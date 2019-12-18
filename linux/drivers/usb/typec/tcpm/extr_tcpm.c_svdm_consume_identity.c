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
typedef  int u32 ;
struct TYPE_2__ {int id_header; int product; void* cert_stat; } ;
struct tcpm_port {int /*<<< orphan*/  partner; TYPE_1__ partner_ident; int /*<<< orphan*/  mode_data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  PD_IDH_VID (int) ; 
 int /*<<< orphan*/  PD_PRODUCT_PID (int) ; 
 size_t VDO_INDEX_CSTAT ; 
 size_t VDO_INDEX_IDH ; 
 size_t VDO_INDEX_PRODUCT ; 
 void* le32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcpm_log (struct tcpm_port*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  typec_partner_set_identity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svdm_consume_identity(struct tcpm_port *port, const __le32 *payload,
				  int cnt)
{
	u32 vdo = le32_to_cpu(payload[VDO_INDEX_IDH]);
	u32 product = le32_to_cpu(payload[VDO_INDEX_PRODUCT]);

	memset(&port->mode_data, 0, sizeof(port->mode_data));

	port->partner_ident.id_header = vdo;
	port->partner_ident.cert_stat = le32_to_cpu(payload[VDO_INDEX_CSTAT]);
	port->partner_ident.product = product;

	typec_partner_set_identity(port->partner);

	tcpm_log(port, "Identity: %04x:%04x.%04x",
		 PD_IDH_VID(vdo),
		 PD_PRODUCT_PID(product), product & 0xffff);
}