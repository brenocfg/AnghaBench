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
typedef  int /*<<< orphan*/  u32 ;
struct vbg_session {int /*<<< orphan*/  requestor; struct vbg_dev* gdev; } ;
struct vbg_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct vbg_session* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vbg_session* kzalloc (int,int /*<<< orphan*/ ) ; 

struct vbg_session *vbg_core_open_session(struct vbg_dev *gdev, u32 requestor)
{
	struct vbg_session *session;

	session = kzalloc(sizeof(*session), GFP_KERNEL);
	if (!session)
		return ERR_PTR(-ENOMEM);

	session->gdev = gdev;
	session->requestor = requestor;

	return session;
}