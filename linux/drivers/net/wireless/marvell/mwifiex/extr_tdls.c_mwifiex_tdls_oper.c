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
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
#define  MWIFIEX_TDLS_CONFIG_LINK 131 
#define  MWIFIEX_TDLS_CREATE_LINK 130 
#define  MWIFIEX_TDLS_DISABLE_LINK 129 
#define  MWIFIEX_TDLS_ENABLE_LINK 128 
 int mwifiex_tdls_process_config_link (struct mwifiex_private*,int const*) ; 
 int mwifiex_tdls_process_create_link (struct mwifiex_private*,int const*) ; 
 int mwifiex_tdls_process_disable_link (struct mwifiex_private*,int const*) ; 
 int mwifiex_tdls_process_enable_link (struct mwifiex_private*,int const*) ; 

int mwifiex_tdls_oper(struct mwifiex_private *priv, const u8 *peer, u8 action)
{
	switch (action) {
	case MWIFIEX_TDLS_ENABLE_LINK:
		return mwifiex_tdls_process_enable_link(priv, peer);
	case MWIFIEX_TDLS_DISABLE_LINK:
		return mwifiex_tdls_process_disable_link(priv, peer);
	case MWIFIEX_TDLS_CREATE_LINK:
		return mwifiex_tdls_process_create_link(priv, peer);
	case MWIFIEX_TDLS_CONFIG_LINK:
		return mwifiex_tdls_process_config_link(priv, peer);
	}
	return 0;
}