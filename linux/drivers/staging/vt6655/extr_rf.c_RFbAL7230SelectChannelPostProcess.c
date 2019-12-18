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
typedef  scalar_t__ u16 ;
struct vnt_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ CB_MAX_CHANNEL_24G ; 
 int IFRFbWriteEmbedded (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dwAL7230InitTable ; 
 int /*<<< orphan*/ * dwAL7230InitTableAMode ; 

bool RFbAL7230SelectChannelPostProcess(struct vnt_private *priv,
				       u16 byOldChannel,
				       u16 byNewChannel)
{
	bool ret;

	ret = true;

	/* if change between 11 b/g and 11a need to update the following
	 * register
	 * Channel Index 1~14
	 */
	if ((byOldChannel <= CB_MAX_CHANNEL_24G) && (byNewChannel > CB_MAX_CHANNEL_24G)) {
		/* Change from 2.4G to 5G [Reg] */
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[2]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[3]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[5]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[7]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[10]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[12]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTableAMode[15]);
	} else if ((byOldChannel > CB_MAX_CHANNEL_24G) && (byNewChannel <= CB_MAX_CHANNEL_24G)) {
		/* Change from 5G to 2.4G [Reg] */
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[2]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[3]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[5]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[7]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[10]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[12]);
		ret &= IFRFbWriteEmbedded(priv, dwAL7230InitTable[15]);
	}

	return ret;
}