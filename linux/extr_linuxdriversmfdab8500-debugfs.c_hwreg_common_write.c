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
typedef  int uint ;
typedef  int u8 ;
struct hwreg_cfg {int bank; int addr; int fmt; int mask; int shift; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int abx500_get_register_interruptible (struct device*,int,int,int*) ; 
 int abx500_set_register_interruptible (struct device*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int kstrtol (char*,int /*<<< orphan*/ ,int*) ; 
 int kstrtouint (char*,int /*<<< orphan*/ ,int*) ; 
 int kstrtoul (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 scalar_t__ strval_len (char*) ; 

__attribute__((used)) static ssize_t hwreg_common_write(char *b, struct hwreg_cfg *cfg,
		struct device *dev)
{
	uint write, val = 0;
	u8  regvalue;
	int ret;
	struct hwreg_cfg loc = {
		.bank = 0,          /* default: invalid phys addr */
		.addr = 0,          /* default: invalid phys addr */
		.fmt = 0,           /* default: 32bit access, hex output */
		.mask = 0xFFFFFFFF, /* default: no mask */
		.shift = 0,         /* default: no bit shift */
	};

	/* read or write ? */
	if (!strncmp(b, "read ", 5)) {
		write = 0;
		b += 5;
	} else if (!strncmp(b, "write ", 6)) {
		write = 1;
		b += 6;
	} else
		return -EINVAL;

	/* OPTIONS -l|-w|-b -s -m -o */
	while ((*b == ' ') || (*b == '-')) {
		if (*(b-1) != ' ') {
			b++;
			continue;
		}
		if ((!strncmp(b, "-d ", 3)) ||
				(!strncmp(b, "-dec ", 5))) {
			b += (*(b+2) == ' ') ? 3 : 5;
			loc.fmt |= (1<<0);
		} else if ((!strncmp(b, "-h ", 3)) ||
				(!strncmp(b, "-hex ", 5))) {
			b += (*(b+2) == ' ') ? 3 : 5;
			loc.fmt &= ~(1<<0);
		} else if ((!strncmp(b, "-m ", 3)) ||
				(!strncmp(b, "-mask ", 6))) {
			b += (*(b+2) == ' ') ? 3 : 6;
			if (strval_len(b) == 0)
				return -EINVAL;
			ret = kstrtoul(b, 0, &loc.mask);
			if (ret)
				return ret;
		} else if ((!strncmp(b, "-s ", 3)) ||
				(!strncmp(b, "-shift ", 7))) {
			b += (*(b+2) == ' ') ? 3 : 7;
			if (strval_len(b) == 0)
				return -EINVAL;
			ret = kstrtol(b, 0, &loc.shift);
			if (ret)
				return ret;
		} else {
			return -EINVAL;
		}
	}
	/* get arg BANK and ADDRESS */
	if (strval_len(b) == 0)
		return -EINVAL;
	ret = kstrtouint(b, 0, &loc.bank);
	if (ret)
		return ret;
	while (*b == ' ')
		b++;
	if (strval_len(b) == 0)
		return -EINVAL;
	ret = kstrtoul(b, 0, &loc.addr);
	if (ret)
		return ret;

	if (write) {
		while (*b == ' ')
			b++;
		if (strval_len(b) == 0)
			return -EINVAL;
		ret = kstrtouint(b, 0, &val);
		if (ret)
			return ret;
	}

	/* args are ok, update target cfg (mainly for read) */
	*cfg = loc;

#ifdef ABB_HWREG_DEBUG
	pr_warn("HWREG request: %s, %s,\n", (write) ? "write" : "read",
		REG_FMT_DEC(cfg) ? "decimal" : "hexa");
	pr_warn("  addr=0x%08X, mask=0x%X, shift=%d" "value=0x%X\n",
		cfg->addr, cfg->mask, cfg->shift, val);
#endif

	if (!write)
		return 0;

	ret = abx500_get_register_interruptible(dev,
			(u8)cfg->bank, (u8)cfg->addr, &regvalue);
	if (ret < 0) {
		dev_err(dev, "abx500_get_reg fail %d, %d\n",
			ret, __LINE__);
		return -EINVAL;
	}

	if (cfg->shift >= 0) {
		regvalue &= ~(cfg->mask << (cfg->shift));
		val = (val & cfg->mask) << (cfg->shift);
	} else {
		regvalue &= ~(cfg->mask >> (-cfg->shift));
		val = (val & cfg->mask) >> (-cfg->shift);
	}
	val = val | regvalue;

	ret = abx500_set_register_interruptible(dev,
			(u8)cfg->bank, (u8)cfg->addr, (u8)val);
	if (ret < 0) {
		pr_err("abx500_set_reg failed %d, %d", ret, __LINE__);
		return -EINVAL;
	}

	return 0;
}