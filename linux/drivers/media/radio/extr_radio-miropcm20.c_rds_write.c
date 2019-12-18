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
typedef  int u8 ;
struct snd_miro_aci {int dummy; } ;

/* Variables and functions */
 int RDS_CLOCKMASK ; 
 int RDS_DATAMASK ; 
 int /*<<< orphan*/  rds_rawwrite (struct snd_miro_aci*,int) ; 

__attribute__((used)) static int rds_write(struct snd_miro_aci *aci, u8 byte)
{
	u8 sendbuffer[8];
	int i;

	for (i = 7; i >= 0; i--)
		sendbuffer[7 - i] = (byte & (1 << i)) ? RDS_DATAMASK : 0;
	sendbuffer[0] |= RDS_CLOCKMASK;

	for (i = 0; i < 8; i++)
		rds_rawwrite(aci, sendbuffer[i]);
	return 0;
}