#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {TYPE_1__ sin_addr; } ;
struct cxgbi_sock {scalar_t__ csk_family; TYPE_3__ daddr6; TYPE_2__ daddr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int csk_print_ip(struct cxgbi_sock *csk, char *buf)
{
	int len;

	cxgbi_sock_get(csk);
	if (csk->csk_family == AF_INET)
		len = sprintf(buf, "%pI4",
			      &csk->daddr.sin_addr.s_addr);
	else
		len = sprintf(buf, "%pI6",
			      &csk->daddr6.sin6_addr);

	cxgbi_sock_put(csk);

	return len;
}