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
typedef  int /*<<< orphan*/  u16 ;
struct vnt_private {int dummy; } ;

/* Variables and functions */
#define  RF_AIROHA 131 
#define  RF_AIROHA7230 130 
#define  RF_AL2230S 129 
#define  RF_NOTHING 128 
 int RFbAL2230SelectChannel (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int s_bAL7230SelectChannel (struct vnt_private*,int /*<<< orphan*/ ) ; 

bool RFbSelectChannel(struct vnt_private *priv, unsigned char byRFType,
		      u16 byChannel)
{
	bool ret = true;

	switch (byRFType) {
	case RF_AIROHA:
	case RF_AL2230S:
		ret = RFbAL2230SelectChannel(priv, byChannel);
		break;
		/*{{ RobertYu: 20050104 */
	case RF_AIROHA7230:
		ret = s_bAL7230SelectChannel(priv, byChannel);
		break;
		/*}} RobertYu */
	case RF_NOTHING:
		ret = true;
		break;
	default:
		ret = false;
		break;
	}
	return ret;
}