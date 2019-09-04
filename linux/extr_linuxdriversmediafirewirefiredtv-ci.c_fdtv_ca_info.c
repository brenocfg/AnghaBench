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
struct firedtv {int dummy; } ;
struct ca_msg {int /*<<< orphan*/  length; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int avc_ca_info (struct firedtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fdtv_ca_info(struct firedtv *fdtv, void *arg)
{
	struct ca_msg *reply = arg;

	return avc_ca_info(fdtv, reply->msg, &reply->length);
}