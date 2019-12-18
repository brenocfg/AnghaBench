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
struct se_session {int dummy; } ;
struct ibmvscsis_tport {struct ibmvscsis_nexus* ibmv_nexus; } ;
struct ibmvscsis_nexus {struct se_session* se_sess; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  kfree (struct ibmvscsis_nexus*) ; 
 int /*<<< orphan*/  target_remove_session (struct se_session*) ; 

__attribute__((used)) static int ibmvscsis_drop_nexus(struct ibmvscsis_tport *tport)
{
	struct se_session *se_sess;
	struct ibmvscsis_nexus *nexus;

	nexus = tport->ibmv_nexus;
	if (!nexus)
		return -ENODEV;

	se_sess = nexus->se_sess;
	if (!se_sess)
		return -ENODEV;

	/*
	 * Release the SCSI I_T Nexus to the emulated ibmvscsis Target Port
	 */
	target_remove_session(se_sess);
	tport->ibmv_nexus = NULL;
	kfree(nexus);

	return 0;
}