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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct zfcp_port {int /*<<< orphan*/  d_id; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  status; } ;
struct zfcp_adapter {int /*<<< orphan*/  erp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_ERP_ACTION_NONE ; 
 int /*<<< orphan*/  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_trig (char*,struct zfcp_adapter*,struct zfcp_port*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zfcp_erp_port_forced_no_port_dbf(char *dbftag,
				      struct zfcp_adapter *adapter,
				      u64 port_name, u32 port_id)
{
	unsigned long flags;
	static /* don't waste stack */ struct zfcp_port tmpport;

	write_lock_irqsave(&adapter->erp_lock, flags);
	/* Stand-in zfcp port with fields just good enough for
	 * zfcp_dbf_rec_trig() and zfcp_dbf_set_common().
	 * Under lock because tmpport is static.
	 */
	atomic_set(&tmpport.status, -1); /* unknown */
	tmpport.wwpn = port_name;
	tmpport.d_id = port_id;
	zfcp_dbf_rec_trig(dbftag, adapter, &tmpport, NULL,
			  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED,
			  ZFCP_ERP_ACTION_NONE);
	write_unlock_irqrestore(&adapter->erp_lock, flags);
}