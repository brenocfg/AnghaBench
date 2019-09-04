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
typedef  int u16 ;
struct xc4000_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XREG_VERSION ; 
 int xc4000_readreg (struct xc4000_priv*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int xc_get_version(struct xc4000_priv *priv,
	u8 *hw_majorversion, u8 *hw_minorversion,
	u8 *fw_majorversion, u8 *fw_minorversion)
{
	u16 data;
	int result;

	result = xc4000_readreg(priv, XREG_VERSION, &data);
	if (result != 0)
		return result;

	(*hw_majorversion) = (data >> 12) & 0x0F;
	(*hw_minorversion) = (data >>  8) & 0x0F;
	(*fw_majorversion) = (data >>  4) & 0x0F;
	(*fw_minorversion) = data & 0x0F;

	return 0;
}