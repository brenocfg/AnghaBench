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
struct cm_rep_msg {int dummy; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int IB_QPT_XRC_INI ; 
 int /*<<< orphan*/  cm_rep_get_local_eecn (struct cm_rep_msg*) ; 
 int /*<<< orphan*/  cm_rep_get_local_qpn (struct cm_rep_msg*) ; 

__attribute__((used)) static inline __be32 cm_rep_get_qpn(struct cm_rep_msg *rep_msg, enum ib_qp_type qp_type)
{
	return (qp_type == IB_QPT_XRC_INI) ?
		cm_rep_get_local_eecn(rep_msg) : cm_rep_get_local_qpn(rep_msg);
}