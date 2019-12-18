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
struct sge_rspq {int gen; } ;
struct rsp_desc {int intr_gen; } ;

/* Variables and functions */
 int F_RSPD_GEN2 ; 

__attribute__((used)) static inline int is_new_response(const struct rsp_desc *r,
				  const struct sge_rspq *q)
{
	return (r->intr_gen & F_RSPD_GEN2) == q->gen;
}