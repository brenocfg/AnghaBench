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
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int nlp_flag; int /*<<< orphan*/  nlp_portname; int /*<<< orphan*/  nlp_nodename; } ;
struct lpfc_name {int dummy; } ;

/* Variables and functions */
 int NLP_RPI_REGISTERED ; 
 scalar_t__ memcmp (struct lpfc_name*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lpfc_check_adisc(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
		 struct lpfc_name *nn, struct lpfc_name *pn)
{
	/* First, we MUST have a RPI registered */
	if (!(ndlp->nlp_flag & NLP_RPI_REGISTERED))
		return 0;

	/* Compare the ADISC rsp WWNN / WWPN matches our internal node
	 * table entry for that node.
	 */
	if (memcmp(nn, &ndlp->nlp_nodename, sizeof (struct lpfc_name)))
		return 0;

	if (memcmp(pn, &ndlp->nlp_portname, sizeof (struct lpfc_name)))
		return 0;

	/* we match, return success */
	return 1;
}