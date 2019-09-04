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
struct atmel_mci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMCI_VERSION ; 
 int atmci_readl (struct atmel_mci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int atmci_get_version(struct atmel_mci *host)
{
	return atmci_readl(host, ATMCI_VERSION) & 0x00000fff;
}