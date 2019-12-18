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
struct snd_miro_aci {int dummy; } ;

/* Variables and functions */
 scalar_t__ rds_rawwrite (struct snd_miro_aci*,int /*<<< orphan*/ ) ; 
 int rds_waitread (struct snd_miro_aci*) ; 

__attribute__((used)) static int rds_readcycle(struct snd_miro_aci *aci)
{
	if (rds_rawwrite(aci, 0) < 0)
		return -1;
	return rds_waitread(aci);
}