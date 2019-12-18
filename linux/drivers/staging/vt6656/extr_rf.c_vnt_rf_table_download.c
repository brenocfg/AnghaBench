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
typedef  int u16 ;
struct vnt_private {int rf_type; } ;

/* Variables and functions */
 int CB_AL2230_INIT_SEQ ; 
 int CB_AL7230_INIT_SEQ ; 
 int CB_MAX_CHANNEL ; 
 int CB_MAX_CHANNEL_24G ; 
 int CB_VT3226_INIT_SEQ ; 
 int CB_VT3342_INIT_SEQ ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_RF_CH0 ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_RF_CH1 ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_RF_CH2 ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_RF_INIT ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_RF_INIT2 ; 
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE ; 
#define  RF_AIROHA7230 133 
#define  RF_AL2230 132 
#define  RF_AL2230S 131 
#define  RF_VT3226 130 
#define  RF_VT3226D0 129 
#define  RF_VT3342A0 128 
 int /*<<< orphan*/ ** al2230_channel_table0 ; 
 int /*<<< orphan*/ ** al2230_channel_table1 ; 
 int /*<<< orphan*/ ** al2230_init_table ; 
 int /*<<< orphan*/ ** al7230_channel_table0 ; 
 int /*<<< orphan*/ ** al7230_channel_table1 ; 
 int /*<<< orphan*/ ** al7230_channel_table2 ; 
 int /*<<< orphan*/ ** al7230_init_table ; 
 int /*<<< orphan*/ ** al7230_init_table_amode ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** vt3226_channel_table0 ; 
 int /*<<< orphan*/ ** vt3226_channel_table1 ; 
 int /*<<< orphan*/ ** vt3226_init_table ; 
 int /*<<< orphan*/ ** vt3226d0_init_table ; 
 int /*<<< orphan*/ ** vt3342_channel_table0 ; 
 int /*<<< orphan*/ ** vt3342_channel_table1 ; 
 int /*<<< orphan*/ ** vt3342a0_init_table ; 

int vnt_rf_table_download(struct vnt_private *priv)
{
	int ret = 0;
	u16 length1 = 0, length2 = 0, length3 = 0;
	u8 *addr1 = NULL, *addr2 = NULL, *addr3 = NULL;
	u16 length, value;
	u8 array[256];

	switch (priv->rf_type) {
	case RF_AL2230:
	case RF_AL2230S:
		length1 = CB_AL2230_INIT_SEQ * 3;
		length2 = CB_MAX_CHANNEL_24G * 3;
		length3 = CB_MAX_CHANNEL_24G * 3;
		addr1 = &al2230_init_table[0][0];
		addr2 = &al2230_channel_table0[0][0];
		addr3 = &al2230_channel_table1[0][0];
		break;
	case RF_AIROHA7230:
		length1 = CB_AL7230_INIT_SEQ * 3;
		length2 = CB_MAX_CHANNEL * 3;
		length3 = CB_MAX_CHANNEL * 3;
		addr1 = &al7230_init_table[0][0];
		addr2 = &al7230_channel_table0[0][0];
		addr3 = &al7230_channel_table1[0][0];
		break;
	case RF_VT3226:
		length1 = CB_VT3226_INIT_SEQ * 3;
		length2 = CB_MAX_CHANNEL_24G * 3;
		length3 = CB_MAX_CHANNEL_24G * 3;
		addr1 = &vt3226_init_table[0][0];
		addr2 = &vt3226_channel_table0[0][0];
		addr3 = &vt3226_channel_table1[0][0];
		break;
	case RF_VT3226D0:
		length1 = CB_VT3226_INIT_SEQ * 3;
		length2 = CB_MAX_CHANNEL_24G * 3;
		length3 = CB_MAX_CHANNEL_24G * 3;
		addr1 = &vt3226d0_init_table[0][0];
		addr2 = &vt3226_channel_table0[0][0];
		addr3 = &vt3226_channel_table1[0][0];
		break;
	case RF_VT3342A0:
		length1 = CB_VT3342_INIT_SEQ * 3;
		length2 = CB_MAX_CHANNEL * 3;
		length3 = CB_MAX_CHANNEL * 3;
		addr1 = &vt3342a0_init_table[0][0];
		addr2 = &vt3342_channel_table0[0][0];
		addr3 = &vt3342_channel_table1[0][0];
		break;
	}

	/* Init Table */
	memcpy(array, addr1, length1);

	ret = vnt_control_out(priv, MESSAGE_TYPE_WRITE, 0,
			      MESSAGE_REQUEST_RF_INIT, length1, array);
	if (ret)
		goto end;

	/* Channel Table 0 */
	value = 0;
	while (length2 > 0) {
		if (length2 >= 64)
			length = 64;
		else
			length = length2;

		memcpy(array, addr2, length);

		ret = vnt_control_out(priv, MESSAGE_TYPE_WRITE, value,
				      MESSAGE_REQUEST_RF_CH0, length, array);
		if (ret)
			goto end;

		length2 -= length;
		value += length;
		addr2 += length;
	}

	/* Channel table 1 */
	value = 0;
	while (length3 > 0) {
		if (length3 >= 64)
			length = 64;
		else
			length = length3;

		memcpy(array, addr3, length);

		ret = vnt_control_out(priv, MESSAGE_TYPE_WRITE, value,
				      MESSAGE_REQUEST_RF_CH1, length, array);
		if (ret)
			goto end;

		length3 -= length;
		value += length;
		addr3 += length;
	}

	if (priv->rf_type == RF_AIROHA7230) {
		length1 = CB_AL7230_INIT_SEQ * 3;
		length2 = CB_MAX_CHANNEL * 3;
		addr1 = &al7230_init_table_amode[0][0];
		addr2 = &al7230_channel_table2[0][0];

		memcpy(array, addr1, length1);

		/* Init Table 2 */
		ret = vnt_control_out(priv, MESSAGE_TYPE_WRITE, 0,
				      MESSAGE_REQUEST_RF_INIT2, length1, array);
		if (ret)
			goto end;

		/* Channel Table 0 */
		value = 0;
		while (length2 > 0) {
			if (length2 >= 64)
				length = 64;
			else
				length = length2;

			memcpy(array, addr2, length);

			ret = vnt_control_out(priv, MESSAGE_TYPE_WRITE, value,
					      MESSAGE_REQUEST_RF_CH2, length,
					      array);
			if (ret)
				goto end;

			length2 -= length;
			value += length;
			addr2 += length;
		}
	}

end:
	return ret;
}