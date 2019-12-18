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
struct registry_priv {scalar_t__ wifi_spec; } ;
struct adapter {struct registry_priv registrypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  one_out_pipe (struct adapter*) ; 
 int /*<<< orphan*/  three_out_pipe (struct adapter*,int) ; 
 int /*<<< orphan*/  two_out_pipe (struct adapter*,int) ; 

bool hal_mapping_out_pipe(struct adapter *adapter, u8 numoutpipe)
{
	struct registry_priv *pregistrypriv = &adapter->registrypriv;
	bool wifi_cfg = (pregistrypriv->wifi_spec) ? true : false;
	bool result = true;

	switch (numoutpipe) {
	case 1:
		one_out_pipe(adapter);
		break;
	case 2:
		two_out_pipe(adapter, wifi_cfg);
		break;
	case 3:
		three_out_pipe(adapter, wifi_cfg);
		break;
	default:
		result = false;
	}
	return result;
}