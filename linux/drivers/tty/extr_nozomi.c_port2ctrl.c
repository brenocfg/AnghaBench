#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nozomi {TYPE_1__* pdev; } ;
typedef  enum port_type { ____Placeholder_port_type } port_type ;
typedef  enum ctrl_port_type { ____Placeholder_ctrl_port_type } ctrl_port_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTRL_APP1 ; 
 int CTRL_APP2 ; 
 int CTRL_DIAG ; 
 int CTRL_ERROR ; 
 int CTRL_MDM ; 
#define  PORT_APP1 131 
#define  PORT_APP2 130 
#define  PORT_DIAG 129 
#define  PORT_MDM 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static enum ctrl_port_type port2ctrl(enum port_type port,
					const struct nozomi *dc)
{
	switch (port) {
	case PORT_MDM:
		return CTRL_MDM;
	case PORT_DIAG:
		return CTRL_DIAG;
	case PORT_APP1:
		return CTRL_APP1;
	case PORT_APP2:
		return CTRL_APP2;
	default:
		dev_err(&dc->pdev->dev,
			"ERROR: send flow control " \
			"received for non-existing port\n");
	}
	return CTRL_ERROR;
}