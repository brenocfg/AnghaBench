#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct fpgaimage {int lendata; scalar_t__ fpgadata; } ;
typedef  enum wbus { ____Placeholder_wbus } wbus ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EINVAL ; 
 int EIO ; 
 int MAX_WAIT_DONE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xl_csi_b (int /*<<< orphan*/ ) ; 
 scalar_t__ xl_get_done_b () ; 
 scalar_t__ xl_get_init_b () ; 
 int /*<<< orphan*/  xl_program_b (int) ; 
 int /*<<< orphan*/  xl_rdwr_b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xl_shift_bytes_out (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xl_shift_cclk (int) ; 
 int /*<<< orphan*/  xl_supported_prog_bus_width (int) ; 

__attribute__((used)) static int gs_download_image(struct fpgaimage *fimage, enum wbus bus_bytes)
{
	u8 *bitdata;
	int size, i, cnt;

	cnt = 0;
	bitdata = (u8 *)fimage->fpgadata;
	size = fimage->lendata;

#ifdef DEBUG_FPGA
	print_hex_dump_bytes("bitfile sample: ", DUMP_PREFIX_OFFSET,
			     bitdata, 0x100);
#endif /* DEBUG_FPGA */
	if (!xl_supported_prog_bus_width(bus_bytes)) {
		pr_err("unsupported program bus width %d\n",
		       bus_bytes);
		return -EINVAL;
	}

	/* Bring csi_b, rdwr_b Low and program_b High */
	xl_program_b(1);
	xl_rdwr_b(0);
	xl_csi_b(0);

	/* Configuration reset */
	xl_program_b(0);
	msleep(20);
	xl_program_b(1);

	/* Wait for Device Initialization */
	while (xl_get_init_b() == 0)
		;

	pr_info("device init done\n");

	for (i = 0; i < size; i += bus_bytes)
		xl_shift_bytes_out(bus_bytes, bitdata + i);

	pr_info("program done\n");

	/* Check INIT_B */
	if (xl_get_init_b() == 0) {
		pr_err("init_b 0\n");
		return -EIO;
	}

	while (xl_get_done_b() == 0) {
		if (cnt++ > MAX_WAIT_DONE) {
			pr_err("init_B %d\n", xl_get_init_b());
			break;
		}
	}

	if (cnt > MAX_WAIT_DONE) {
		pr_err("fpga download fail\n");
		return -EIO;
	}

	pr_info("download fpgaimage\n");

	/* Compensate for Special Startup Conditions */
	xl_shift_cclk(8);

	return 0;
}