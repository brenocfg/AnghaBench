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
struct fcloop_fcpreq {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int kref_get_unless_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fcloop_tfcp_req_get(struct fcloop_fcpreq *tfcp_req)
{
	return kref_get_unless_zero(&tfcp_req->ref);
}