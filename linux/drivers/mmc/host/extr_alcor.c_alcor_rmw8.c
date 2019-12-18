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
typedef  int /*<<< orphan*/  u32 ;
struct alcor_sdmmc_host {struct alcor_pci_priv* alcor_pci; } ;
struct alcor_pci_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alcor_read8 (struct alcor_pci_priv*,unsigned int) ; 
 int /*<<< orphan*/  alcor_write8 (struct alcor_pci_priv*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void alcor_rmw8(struct alcor_sdmmc_host *host, unsigned int addr,
			       u8 clear, u8 set)
{
	struct alcor_pci_priv *priv = host->alcor_pci;
	u32 var;

	var = alcor_read8(priv, addr);
	var &= ~clear;
	var |= set;
	alcor_write8(priv, var, addr);
}