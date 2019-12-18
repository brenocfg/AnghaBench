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
struct sclp_req {int /*<<< orphan*/  sccb; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (struct completion*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sclp_ftp_txcb(struct sclp_req *req, void *data)
{
	struct completion *completion = data;

#ifdef DEBUG
	pr_debug("SCLP (ET7) TX-IRQ, SCCB @ 0x%p: %*phN\n",
		 req->sccb, 24, req->sccb);
#endif
	complete(completion);
}