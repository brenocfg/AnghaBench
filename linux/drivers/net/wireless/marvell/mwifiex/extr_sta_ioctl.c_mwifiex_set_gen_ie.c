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
struct mwifiex_private {int dummy; } ;
struct mwifiex_ds_misc_gen_ie {int len; int /*<<< orphan*/  ie_data; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int IEEE_MAX_IE_SIZE ; 
 int /*<<< orphan*/  MWIFIEX_IE_TYPE_GEN_IE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ mwifiex_misc_ioctl_gen_ie (struct mwifiex_private*,struct mwifiex_ds_misc_gen_ie*,int /*<<< orphan*/ ) ; 

int
mwifiex_set_gen_ie(struct mwifiex_private *priv, const u8 *ie, int ie_len)
{
	struct mwifiex_ds_misc_gen_ie gen_ie;

	if (ie_len > IEEE_MAX_IE_SIZE)
		return -EFAULT;

	gen_ie.type = MWIFIEX_IE_TYPE_GEN_IE;
	gen_ie.len = ie_len;
	memcpy(gen_ie.ie_data, ie, ie_len);
	if (mwifiex_misc_ioctl_gen_ie(priv, &gen_ie, HostCmd_ACT_GEN_SET))
		return -EFAULT;

	return 0;
}