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
struct vnt_private {int dummy; } ;

/* Variables and functions */
 unsigned char ANT_A ; 
 unsigned char ANT_B ; 
 unsigned char ANT_DIVERSITY ; 
 int /*<<< orphan*/  BBbReadEmbedded (struct vnt_private*,int,unsigned char*) ; 
 int /*<<< orphan*/  BBbWriteEmbedded (struct vnt_private*,int,unsigned char) ; 

void
BBvSetRxAntennaMode(struct vnt_private *priv, unsigned char byAntennaMode)
{
	unsigned char byBBRxConf;

	BBbReadEmbedded(priv, 0x0A, &byBBRxConf); /* CR10 */
	if (byAntennaMode == ANT_DIVERSITY) {
		byBBRxConf |= 0x01;

	} else if (byAntennaMode == ANT_A) {
		byBBRxConf &= 0xFC; /* 1111 1100 */
	} else if (byAntennaMode == ANT_B) {
		byBBRxConf &= 0xFE; /* 1111 1110 */
		byBBRxConf |= 0x02;
	}
	BBbWriteEmbedded(priv, 0x0A, byBBRxConf); /* CR10 */
}