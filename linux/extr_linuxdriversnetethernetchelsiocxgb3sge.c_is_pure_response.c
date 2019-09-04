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
struct rsp_desc {int flags; int len_cq; } ;
typedef  int __be32 ;

/* Variables and functions */
 int F_RSPD_ASYNC_NOTIF ; 
 int F_RSPD_IMM_DATA_VALID ; 
 int htonl (int) ; 

__attribute__((used)) static inline int is_pure_response(const struct rsp_desc *r)
{
	__be32 n = r->flags & htonl(F_RSPD_ASYNC_NOTIF | F_RSPD_IMM_DATA_VALID);

	return (n | r->len_cq) == 0;
}