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
struct ptd {int dummy; } ;
struct isp1760_qtd {int dummy; } ;
struct isp1760_qh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_ptd_atl (struct isp1760_qh*,struct isp1760_qtd*,struct ptd*) ; 
 int /*<<< orphan*/  transform_add_int (struct isp1760_qh*,struct isp1760_qtd*,struct ptd*) ; 

__attribute__((used)) static void create_ptd_int(struct isp1760_qh *qh,
			struct isp1760_qtd *qtd, struct ptd *ptd)
{
	create_ptd_atl(qh, qtd, ptd);
	transform_add_int(qh, qtd, ptd);
}