#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct slic_device {scalar_t__ model; TYPE_1__* pdev; } ;
struct firmware {unsigned int size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int SLIC_FIRMWARE_MAX_SECTIONS ; 
 unsigned int SLIC_FIRMWARE_MIN_SIZE ; 
 char* SLIC_FIRMWARE_MOJAVE ; 
 char* SLIC_FIRMWARE_OASIS ; 
 scalar_t__ SLIC_MODEL_OASIS ; 
 int /*<<< orphan*/  SLIC_REG_WCS ; 
 int SLIC_WCS_COMPARE ; 
 int SLIC_WCS_START ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slic_flush_write (struct slic_device*) ; 
 int slic_read_dword_from_firmware (struct firmware const*,int*) ; 
 int /*<<< orphan*/  slic_write (struct slic_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int slic_load_firmware(struct slic_device *sdev)
{
	u32 sectstart[SLIC_FIRMWARE_MAX_SECTIONS];
	u32 sectsize[SLIC_FIRMWARE_MAX_SECTIONS];
	const struct firmware *fw;
	unsigned int datalen;
	const char *file;
	int code_start;
	unsigned int i;
	u32 numsects;
	int idx = 0;
	u32 sect;
	u32 instr;
	u32 addr;
	u32 base;
	int err;

	file = (sdev->model == SLIC_MODEL_OASIS) ?  SLIC_FIRMWARE_OASIS :
						    SLIC_FIRMWARE_MOJAVE;
	err = request_firmware(&fw, file, &sdev->pdev->dev);
	if (err) {
		dev_err(&sdev->pdev->dev, "failed to load firmware %s\n", file);
		return err;
	}
	/* Do an initial sanity check concerning firmware size now. A further
	 * check follows below.
	 */
	if (fw->size < SLIC_FIRMWARE_MIN_SIZE) {
		dev_err(&sdev->pdev->dev,
			"invalid firmware size %zu (min is %u)\n", fw->size,
			SLIC_FIRMWARE_MIN_SIZE);
		err = -EINVAL;
		goto release;
	}

	numsects = slic_read_dword_from_firmware(fw, &idx);
	if (numsects == 0 || numsects > SLIC_FIRMWARE_MAX_SECTIONS) {
		dev_err(&sdev->pdev->dev,
			"invalid number of sections in firmware: %u", numsects);
		err = -EINVAL;
		goto release;
	}

	datalen = numsects * 8 + 4;
	for (i = 0; i < numsects; i++) {
		sectsize[i] = slic_read_dword_from_firmware(fw, &idx);
		datalen += sectsize[i];
	}

	/* do another sanity check against firmware size */
	if (datalen > fw->size) {
		dev_err(&sdev->pdev->dev,
			"invalid firmware size %zu (expected >= %u)\n",
			fw->size, datalen);
		err = -EINVAL;
		goto release;
	}
	/* get sections */
	for (i = 0; i < numsects; i++)
		sectstart[i] = slic_read_dword_from_firmware(fw, &idx);

	code_start = idx;
	instr = slic_read_dword_from_firmware(fw, &idx);

	for (sect = 0; sect < numsects; sect++) {
		unsigned int ssize = sectsize[sect] >> 3;

		base = sectstart[sect];

		for (addr = 0; addr < ssize; addr++) {
			/* write out instruction address */
			slic_write(sdev, SLIC_REG_WCS, base + addr);
			/* write out instruction to low addr */
			slic_write(sdev, SLIC_REG_WCS, instr);
			instr = slic_read_dword_from_firmware(fw, &idx);
			/* write out instruction to high addr */
			slic_write(sdev, SLIC_REG_WCS, instr);
			instr = slic_read_dword_from_firmware(fw, &idx);
		}
	}

	idx = code_start;

	for (sect = 0; sect < numsects; sect++) {
		unsigned int ssize = sectsize[sect] >> 3;

		instr = slic_read_dword_from_firmware(fw, &idx);
		base = sectstart[sect];
		if (base < 0x8000)
			continue;

		for (addr = 0; addr < ssize; addr++) {
			/* write out instruction address */
			slic_write(sdev, SLIC_REG_WCS,
				   SLIC_WCS_COMPARE | (base + addr));
			/* write out instruction to low addr */
			slic_write(sdev, SLIC_REG_WCS, instr);
			instr = slic_read_dword_from_firmware(fw, &idx);
			/* write out instruction to high addr */
			slic_write(sdev, SLIC_REG_WCS, instr);
			instr = slic_read_dword_from_firmware(fw, &idx);
		}
	}
	slic_flush_write(sdev);
	mdelay(10);
	/* everything OK, kick off the card */
	slic_write(sdev, SLIC_REG_WCS, SLIC_WCS_START);
	slic_flush_write(sdev);
	/* wait long enough for ucode to init card and reach the mainloop */
	mdelay(20);
release:
	release_firmware(fw);

	return err;
}