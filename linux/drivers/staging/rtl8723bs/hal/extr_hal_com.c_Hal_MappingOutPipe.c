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
 int /*<<< orphan*/  _OneOutPipeMapping (struct adapter*) ; 
 int /*<<< orphan*/  _ThreeOutPipeMapping (struct adapter*,int) ; 
 int /*<<< orphan*/  _TwoOutPipeMapping (struct adapter*,int) ; 

bool Hal_MappingOutPipe(struct adapter *padapter, u8 NumOutPipe)
{
	struct registry_priv *pregistrypriv = &padapter->registrypriv;

	bool bWIFICfg = (pregistrypriv->wifi_spec) ? true : false;

	bool result = true;

	switch (NumOutPipe) {
	case 2:
		_TwoOutPipeMapping(padapter, bWIFICfg);
		break;
	case 3:
	case 4:
		_ThreeOutPipeMapping(padapter, bWIFICfg);
		break;
	case 1:
		_OneOutPipeMapping(padapter);
		break;
	default:
		result = false;
		break;
	}

	return result;

}