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
typedef  int u64 ;
typedef  int u32 ;
struct uniphier_system_bus_priv {TYPE_1__* bank; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int base; int end; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int U32_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int round_down (int,int) ; 
 int round_up (int,int) ; 
 int roundup_pow_of_two (int) ; 

__attribute__((used)) static int uniphier_system_bus_add_bank(struct uniphier_system_bus_priv *priv,
					int bank, u32 addr, u64 paddr, u32 size)
{
	u64 end, mask;

	dev_dbg(priv->dev,
		"range found: bank = %d, addr = %08x, paddr = %08llx, size = %08x\n",
		bank, addr, paddr, size);

	if (bank >= ARRAY_SIZE(priv->bank)) {
		dev_err(priv->dev, "unsupported bank number %d\n", bank);
		return -EINVAL;
	}

	if (priv->bank[bank].base || priv->bank[bank].end) {
		dev_err(priv->dev,
			"range for bank %d has already been specified\n", bank);
		return -EINVAL;
	}

	if (paddr > U32_MAX) {
		dev_err(priv->dev, "base address %llx is too high\n", paddr);
		return -EINVAL;
	}

	end = paddr + size;

	if (addr > paddr) {
		dev_err(priv->dev,
			"base %08x cannot be mapped to %08llx of parent\n",
			addr, paddr);
		return -EINVAL;
	}
	paddr -= addr;

	paddr = round_down(paddr, 0x00020000);
	end = round_up(end, 0x00020000);

	if (end > U32_MAX) {
		dev_err(priv->dev, "end address %08llx is too high\n", end);
		return -EINVAL;
	}
	mask = paddr ^ (end - 1);
	mask = roundup_pow_of_two(mask);

	paddr = round_down(paddr, mask);
	end = round_up(end, mask);

	priv->bank[bank].base = paddr;
	priv->bank[bank].end = end;

	dev_dbg(priv->dev, "range added: bank = %d, addr = %08x, end = %08x\n",
		bank, priv->bank[bank].base, priv->bank[bank].end);

	return 0;
}