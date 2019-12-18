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
struct nfp_qdisc {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NFP_QDISC_GRED ; 
 scalar_t__ NFP_QDISC_RED ; 

__attribute__((used)) static bool nfp_abm_qdisc_is_red(struct nfp_qdisc *qdisc)
{
	return qdisc->type == NFP_QDISC_RED || qdisc->type == NFP_QDISC_GRED;
}