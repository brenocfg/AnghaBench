#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct attribute_container {int /*<<< orphan*/ * class; } ;
struct TYPE_3__ {struct attribute_container ac; } ;
struct iscsi_internal {TYPE_1__ session_cont; } ;
struct iscsi_cls_session {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
struct TYPE_4__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 struct iscsi_cls_session* iscsi_dev_to_session (struct device*) ; 
 int /*<<< orphan*/  iscsi_is_session_dev (struct device*) ; 
 TYPE_2__ iscsi_session_class ; 
 struct Scsi_Host* iscsi_session_to_shost (struct iscsi_cls_session*) ; 
 struct iscsi_internal* to_iscsi_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_session_match(struct attribute_container *cont,
			   struct device *dev)
{
	struct iscsi_cls_session *session;
	struct Scsi_Host *shost;
	struct iscsi_internal *priv;

	if (!iscsi_is_session_dev(dev))
		return 0;

	session = iscsi_dev_to_session(dev);
	shost = iscsi_session_to_shost(session);
	if (!shost->transportt)
		return 0;

	priv = to_iscsi_internal(shost->transportt);
	if (priv->session_cont.ac.class != &iscsi_session_class.class)
		return 0;

	return &priv->session_cont.ac == cont;
}