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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_CTRL ; 
 int /*<<< orphan*/  EFUSE_GetEfuseDefinition (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  EFUSE_WIFI ; 
 int /*<<< orphan*/  TYPE_EFUSE_REAL_CONTENT_LEN ; 
 int rtw_read8 (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,scalar_t__,int) ; 

u8
EFUSE_Read1Byte(
struct adapter *Adapter,
u16 	Address)
{
	u8 Bytetemp = {0x00};
	u8 temp = {0x00};
	u32 k = 0;
	u16 contentLen = 0;

	EFUSE_GetEfuseDefinition(Adapter, EFUSE_WIFI, TYPE_EFUSE_REAL_CONTENT_LEN, (void *)&contentLen, false);

	if (Address < contentLen) {/* E-fuse 512Byte */
		/* Write E-fuse Register address bit0~7 */
		temp = Address & 0xFF;
		rtw_write8(Adapter, EFUSE_CTRL+1, temp);
		Bytetemp = rtw_read8(Adapter, EFUSE_CTRL+2);
		/* Write E-fuse Register address bit8~9 */
		temp = ((Address >> 8) & 0x03) | (Bytetemp & 0xFC);
		rtw_write8(Adapter, EFUSE_CTRL+2, temp);

		/* Write 0x30[31]= 0 */
		Bytetemp = rtw_read8(Adapter, EFUSE_CTRL+3);
		temp = Bytetemp & 0x7F;
		rtw_write8(Adapter, EFUSE_CTRL+3, temp);

		/* Wait Write-ready (0x30[31]= 1) */
		Bytetemp = rtw_read8(Adapter, EFUSE_CTRL+3);
		while (!(Bytetemp & 0x80)) {
			Bytetemp = rtw_read8(Adapter, EFUSE_CTRL+3);
			k++;
			if (k == 1000) {
				k = 0;
				break;
			}
		}
		return rtw_read8(Adapter, EFUSE_CTRL);
	} else
		return 0xFF;

}