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
struct snd_miro_aci {scalar_t__ aci_port; } ;

/* Variables and functions */
 scalar_t__ ACI_REG_RDS ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rds_waitread (struct snd_miro_aci*) ; 

__attribute__((used)) static int rds_rawwrite(struct snd_miro_aci *aci, u8 byte)
{
	if (rds_waitread(aci) >= 0) {
		outb(byte, aci->aci_port + ACI_REG_RDS);
		return 0;
	}
	return -1;
}