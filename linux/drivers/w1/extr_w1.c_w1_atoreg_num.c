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
typedef  int /*<<< orphan*/  u64 ;
struct w1_reg_num {unsigned int family; unsigned long long id; int /*<<< orphan*/  crc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned int,unsigned long long,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned long long*) ; 
 int /*<<< orphan*/  w1_calc_crc8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int w1_atoreg_num(struct device *dev, const char *buf, size_t count,
	struct w1_reg_num *rn)
{
	unsigned int family;
	unsigned long long id;
	int i;
	u64 rn64_le;

	/* The CRC value isn't read from the user because the sysfs directory
	 * doesn't include it and most messages from the bus search don't
	 * print it either.  It would be unreasonable for the user to then
	 * provide it.
	 */
	const char *error_msg = "bad slave string format, expecting "
		"ff-dddddddddddd\n";

	if (buf[2] != '-') {
		dev_err(dev, "%s", error_msg);
		return -EINVAL;
	}
	i = sscanf(buf, "%02x-%012llx", &family, &id);
	if (i != 2) {
		dev_err(dev, "%s", error_msg);
		return -EINVAL;
	}
	rn->family = family;
	rn->id = id;

	rn64_le = cpu_to_le64(*(u64 *)rn);
	rn->crc = w1_calc_crc8((u8 *)&rn64_le, 7);

#if 0
	dev_info(dev, "With CRC device is %02x.%012llx.%02x.\n",
		  rn->family, (unsigned long long)rn->id, rn->crc);
#endif

	return 0;
}