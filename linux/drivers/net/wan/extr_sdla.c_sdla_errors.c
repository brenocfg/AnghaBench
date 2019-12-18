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
struct net_device {int dummy; } ;
struct _dlci_stat {int flags; int /*<<< orphan*/  dlci; } ;

/* Variables and functions */
 int SDLA_DLCI_ACTIVE ; 
 int SDLA_DLCI_DELETED ; 
 int SDLA_DLCI_NEW ; 
 int SDLA_INFORMATION_WRITE ; 
 char SDLA_MODEM_CTS_LOW ; 
 char SDLA_MODEM_DCD_LOW ; 
#define  SDLA_RET_BUF_OVERSIZE 139 
#define  SDLA_RET_BUF_TOO_BIG 138 
#define  SDLA_RET_CHANNEL_INACTIVE 137 
#define  SDLA_RET_CHANNEL_OFF 136 
#define  SDLA_RET_CHANNEL_ON 135 
#define  SDLA_RET_CIR_OVERFLOW 134 
#define  SDLA_RET_DLCI_INACTIVE 133 
#define  SDLA_RET_DLCI_STATUS 132 
#define  SDLA_RET_DLCI_UNKNOWN 131 
#define  SDLA_RET_MODEM 130 
#define  SDLA_RET_NO_BUFS 129 
#define  SDLA_RET_TIMEOUT 128 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void sdla_errors(struct net_device *dev, int cmd, int dlci, int ret, int len, void *data) 
{
	struct _dlci_stat *pstatus;
	short             *pdlci;
	int               i;
	char              *state, line[30];

	switch (ret)
	{
		case SDLA_RET_MODEM:
			state = data;
			if (*state & SDLA_MODEM_DCD_LOW)
				netdev_info(dev, "Modem DCD unexpectedly low!\n");
			if (*state & SDLA_MODEM_CTS_LOW)
				netdev_info(dev, "Modem CTS unexpectedly low!\n");
			/* I should probably do something about this! */
			break;

		case SDLA_RET_CHANNEL_OFF:
			netdev_info(dev, "Channel became inoperative!\n");
			/* same here */
			break;

		case SDLA_RET_CHANNEL_ON:
			netdev_info(dev, "Channel became operative!\n");
			/* same here */
			break;

		case SDLA_RET_DLCI_STATUS:
			netdev_info(dev, "Status change reported by Access Node\n");
			len /= sizeof(struct _dlci_stat);
			for(pstatus = data, i=0;i < len;i++,pstatus++)
			{
				if (pstatus->flags & SDLA_DLCI_NEW)
					state = "new";
				else if (pstatus->flags & SDLA_DLCI_DELETED)
					state = "deleted";
				else if (pstatus->flags & SDLA_DLCI_ACTIVE)
					state = "active";
				else
				{
					sprintf(line, "unknown status: %02X", pstatus->flags);
					state = line;
				}
				netdev_info(dev, "DLCI %i: %s\n",
					    pstatus->dlci, state);
				/* same here */
			}
			break;

		case SDLA_RET_DLCI_UNKNOWN:
			netdev_info(dev, "Received unknown DLCIs:");
			len /= sizeof(short);
			for(pdlci = data,i=0;i < len;i++,pdlci++)
				pr_cont(" %i", *pdlci);
			pr_cont("\n");
			break;

		case SDLA_RET_TIMEOUT:
			netdev_err(dev, "Command timed out!\n");
			break;

		case SDLA_RET_BUF_OVERSIZE:
			netdev_info(dev, "Bc/CIR overflow, acceptable size is %i\n",
				    len);
			break;

		case SDLA_RET_BUF_TOO_BIG:
			netdev_info(dev, "Buffer size over specified max of %i\n",
				    len);
			break;

		case SDLA_RET_CHANNEL_INACTIVE:
		case SDLA_RET_DLCI_INACTIVE:
		case SDLA_RET_CIR_OVERFLOW:
		case SDLA_RET_NO_BUFS:
			if (cmd == SDLA_INFORMATION_WRITE)
				break;
			/* Else, fall through */

		default: 
			netdev_dbg(dev, "Cmd 0x%02X generated return code 0x%02X\n",
				   cmd, ret);
			/* Further processing could be done here */
			break;
	}
}