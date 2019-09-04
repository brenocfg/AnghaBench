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
struct hwrng {scalar_t__ priv; } ;
struct amd768_priv {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd_rng_init(struct hwrng *rng)
{
	struct amd768_priv *priv = (struct amd768_priv *)rng->priv;
	u8 rnen;

	pci_read_config_byte(priv->pcidev, 0x40, &rnen);
	rnen |= BIT(7);	/* RNG on */
	pci_write_config_byte(priv->pcidev, 0x40, rnen);

	pci_read_config_byte(priv->pcidev, 0x41, &rnen);
	rnen |= BIT(7);	/* PMIO enable */
	pci_write_config_byte(priv->pcidev, 0x41, rnen);

	return 0;
}