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
 int RDS_DATAMASK ; 
 int rds_readcycle (struct snd_miro_aci*) ; 

__attribute__((used)) static int rds_ack(struct snd_miro_aci *aci)
{
	int i = rds_readcycle(aci);

	if (i < 0)
		return -1;
	if (i & RDS_DATAMASK)
		return 0;  /* ACK  */
	return 1;  /* NACK */
}