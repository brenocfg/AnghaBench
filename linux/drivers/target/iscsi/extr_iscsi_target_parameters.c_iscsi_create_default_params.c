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
struct iscsi_param_list {int /*<<< orphan*/  extra_response_list; int /*<<< orphan*/  param_list; } ;
struct iscsi_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHMETHOD ; 
 int /*<<< orphan*/  DATADIGEST ; 
 int /*<<< orphan*/  DATAPDUINORDER ; 
 int /*<<< orphan*/  DATASEQUENCEINORDER ; 
 int /*<<< orphan*/  DEFAULTTIME2RETAIN ; 
 int /*<<< orphan*/  DEFAULTTIME2WAIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERRORRECOVERYLEVEL ; 
 int /*<<< orphan*/  FIRSTBURSTLENGTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HEADERDIGEST ; 
 int /*<<< orphan*/  IFMARKER ; 
 int /*<<< orphan*/  IFMARKINT ; 
 int /*<<< orphan*/  IMMEDIATEDATA ; 
 int /*<<< orphan*/  INITIALR2T ; 
 int /*<<< orphan*/  INITIAL_AUTHMETHOD ; 
 int /*<<< orphan*/  INITIAL_DATADIGEST ; 
 int /*<<< orphan*/  INITIAL_DATAPDUINORDER ; 
 int /*<<< orphan*/  INITIAL_DATASEQUENCEINORDER ; 
 int /*<<< orphan*/  INITIAL_DEFAULTTIME2RETAIN ; 
 int /*<<< orphan*/  INITIAL_DEFAULTTIME2WAIT ; 
 int /*<<< orphan*/  INITIAL_ERRORRECOVERYLEVEL ; 
 int /*<<< orphan*/  INITIAL_FIRSTBURSTLENGTH ; 
 int /*<<< orphan*/  INITIAL_HEADERDIGEST ; 
 int /*<<< orphan*/  INITIAL_IFMARKER ; 
 int /*<<< orphan*/  INITIAL_IFMARKINT ; 
 int /*<<< orphan*/  INITIAL_IMMEDIATEDATA ; 
 int /*<<< orphan*/  INITIAL_INITIALR2T ; 
 int /*<<< orphan*/  INITIAL_INITIATORALIAS ; 
 int /*<<< orphan*/  INITIAL_INITIATORNAME ; 
 int /*<<< orphan*/  INITIAL_INITIATORRECVDATASEGMENTLENGTH ; 
 int /*<<< orphan*/  INITIAL_MAXBURSTLENGTH ; 
 int /*<<< orphan*/  INITIAL_MAXCONNECTIONS ; 
 int /*<<< orphan*/  INITIAL_MAXOUTSTANDINGR2T ; 
 int /*<<< orphan*/  INITIAL_MAXRECVDATASEGMENTLENGTH ; 
 int /*<<< orphan*/  INITIAL_MAXXMITDATASEGMENTLENGTH ; 
 int /*<<< orphan*/  INITIAL_OFMARKER ; 
 int /*<<< orphan*/  INITIAL_OFMARKINT ; 
 int /*<<< orphan*/  INITIAL_RDMAEXTENSIONS ; 
 int /*<<< orphan*/  INITIAL_SENDTARGETS ; 
 int /*<<< orphan*/  INITIAL_SESSIONTYPE ; 
 int /*<<< orphan*/  INITIAL_TARGETADDRESS ; 
 int /*<<< orphan*/  INITIAL_TARGETALIAS ; 
 int /*<<< orphan*/  INITIAL_TARGETNAME ; 
 int /*<<< orphan*/  INITIAL_TARGETPORTALGROUPTAG ; 
 int /*<<< orphan*/  INITIAL_TARGETRECVDATASEGMENTLENGTH ; 
 int /*<<< orphan*/  INITIATORALIAS ; 
 int /*<<< orphan*/  INITIATORNAME ; 
 int /*<<< orphan*/  INITIATORRECVDATASEGMENTLENGTH ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXBURSTLENGTH ; 
 int /*<<< orphan*/  MAXCONNECTIONS ; 
 int /*<<< orphan*/  MAXOUTSTANDINGR2T ; 
 int /*<<< orphan*/  MAXRECVDATASEGMENTLENGTH ; 
 int /*<<< orphan*/  MAXXMITDATASEGMENTLENGTH ; 
 int /*<<< orphan*/  OFMARKER ; 
 int /*<<< orphan*/  OFMARKINT ; 
 int /*<<< orphan*/  PHASE_DECLARATIVE ; 
 int /*<<< orphan*/  PHASE_FFP0 ; 
 int /*<<< orphan*/  PHASE_OPERATIONAL ; 
 int /*<<< orphan*/  PHASE_SECURITY ; 
 int /*<<< orphan*/  RDMAEXTENSIONS ; 
 int /*<<< orphan*/  SCOPE_CONNECTION_ONLY ; 
 int /*<<< orphan*/  SCOPE_SESSION_WIDE ; 
 int /*<<< orphan*/  SENDER_BOTH ; 
 int /*<<< orphan*/  SENDER_INITIATOR ; 
 int /*<<< orphan*/  SENDER_TARGET ; 
 int /*<<< orphan*/  SENDTARGETS ; 
 int /*<<< orphan*/  SESSIONTYPE ; 
 int /*<<< orphan*/  TARGETADDRESS ; 
 int /*<<< orphan*/  TARGETALIAS ; 
 int /*<<< orphan*/  TARGETNAME ; 
 int /*<<< orphan*/  TARGETPORTALGROUPTAG ; 
 int /*<<< orphan*/  TARGETRECVDATASEGMENTLENGTH ; 
 int /*<<< orphan*/  TYPERANGE_0_TO_2 ; 
 int /*<<< orphan*/  TYPERANGE_0_TO_3600 ; 
 int /*<<< orphan*/  TYPERANGE_0_TO_65535 ; 
 int /*<<< orphan*/  TYPERANGE_1_TO_65535 ; 
 int /*<<< orphan*/  TYPERANGE_512_TO_16777215 ; 
 int /*<<< orphan*/  TYPERANGE_AUTH ; 
 int /*<<< orphan*/  TYPERANGE_BOOL_AND ; 
 int /*<<< orphan*/  TYPERANGE_BOOL_OR ; 
 int /*<<< orphan*/  TYPERANGE_DIGEST ; 
 int /*<<< orphan*/  TYPERANGE_ISCSINAME ; 
 int /*<<< orphan*/  TYPERANGE_SESSIONTYPE ; 
 int /*<<< orphan*/  TYPERANGE_TARGETADDRESS ; 
 int /*<<< orphan*/  TYPERANGE_UTF8 ; 
 int /*<<< orphan*/  USE_ALL ; 
 int /*<<< orphan*/  USE_INITIAL_ONLY ; 
 int /*<<< orphan*/  USE_LEADING_ONLY ; 
 int /*<<< orphan*/  iscsi_release_param_list (struct iscsi_param_list*) ; 
 struct iscsi_param* iscsi_set_default_param (struct iscsi_param_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iscsi_param_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int iscsi_create_default_params(struct iscsi_param_list **param_list_ptr)
{
	struct iscsi_param *param = NULL;
	struct iscsi_param_list *pl;

	pl = kzalloc(sizeof(struct iscsi_param_list), GFP_KERNEL);
	if (!pl) {
		pr_err("Unable to allocate memory for"
				" struct iscsi_param_list.\n");
		return -ENOMEM;
	}
	INIT_LIST_HEAD(&pl->param_list);
	INIT_LIST_HEAD(&pl->extra_response_list);

	/*
	 * The format for setting the initial parameter definitions are:
	 *
	 * Parameter name:
	 * Initial value:
	 * Allowable phase:
	 * Scope:
	 * Allowable senders:
	 * Typerange:
	 * Use:
	 */
	param = iscsi_set_default_param(pl, AUTHMETHOD, INITIAL_AUTHMETHOD,
			PHASE_SECURITY, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_AUTH, USE_INITIAL_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, HEADERDIGEST, INITIAL_HEADERDIGEST,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_DIGEST, USE_INITIAL_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, DATADIGEST, INITIAL_DATADIGEST,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_DIGEST, USE_INITIAL_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, MAXCONNECTIONS,
			INITIAL_MAXCONNECTIONS, PHASE_OPERATIONAL,
			SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_1_TO_65535, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, SENDTARGETS, INITIAL_SENDTARGETS,
			PHASE_FFP0, SCOPE_SESSION_WIDE, SENDER_INITIATOR,
			TYPERANGE_UTF8, 0);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, TARGETNAME, INITIAL_TARGETNAME,
			PHASE_DECLARATIVE, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_ISCSINAME, USE_ALL);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, INITIATORNAME,
			INITIAL_INITIATORNAME, PHASE_DECLARATIVE,
			SCOPE_SESSION_WIDE, SENDER_INITIATOR,
			TYPERANGE_ISCSINAME, USE_INITIAL_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, TARGETALIAS, INITIAL_TARGETALIAS,
			PHASE_DECLARATIVE, SCOPE_SESSION_WIDE, SENDER_TARGET,
			TYPERANGE_UTF8, USE_ALL);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, INITIATORALIAS,
			INITIAL_INITIATORALIAS, PHASE_DECLARATIVE,
			SCOPE_SESSION_WIDE, SENDER_INITIATOR, TYPERANGE_UTF8,
			USE_ALL);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, TARGETADDRESS,
			INITIAL_TARGETADDRESS, PHASE_DECLARATIVE,
			SCOPE_SESSION_WIDE, SENDER_TARGET,
			TYPERANGE_TARGETADDRESS, USE_ALL);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, TARGETPORTALGROUPTAG,
			INITIAL_TARGETPORTALGROUPTAG,
			PHASE_DECLARATIVE, SCOPE_SESSION_WIDE, SENDER_TARGET,
			TYPERANGE_0_TO_65535, USE_INITIAL_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, INITIALR2T, INITIAL_INITIALR2T,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_BOOL_OR, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, IMMEDIATEDATA,
			INITIAL_IMMEDIATEDATA, PHASE_OPERATIONAL,
			SCOPE_SESSION_WIDE, SENDER_BOTH, TYPERANGE_BOOL_AND,
			USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, MAXXMITDATASEGMENTLENGTH,
			INITIAL_MAXXMITDATASEGMENTLENGTH,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_512_TO_16777215, USE_ALL);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, MAXRECVDATASEGMENTLENGTH,
			INITIAL_MAXRECVDATASEGMENTLENGTH,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_512_TO_16777215, USE_ALL);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, MAXBURSTLENGTH,
			INITIAL_MAXBURSTLENGTH, PHASE_OPERATIONAL,
			SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_512_TO_16777215, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, FIRSTBURSTLENGTH,
			INITIAL_FIRSTBURSTLENGTH,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_512_TO_16777215, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, DEFAULTTIME2WAIT,
			INITIAL_DEFAULTTIME2WAIT,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_0_TO_3600, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, DEFAULTTIME2RETAIN,
			INITIAL_DEFAULTTIME2RETAIN,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_0_TO_3600, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, MAXOUTSTANDINGR2T,
			INITIAL_MAXOUTSTANDINGR2T,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_1_TO_65535, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, DATAPDUINORDER,
			INITIAL_DATAPDUINORDER, PHASE_OPERATIONAL,
			SCOPE_SESSION_WIDE, SENDER_BOTH, TYPERANGE_BOOL_OR,
			USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, DATASEQUENCEINORDER,
			INITIAL_DATASEQUENCEINORDER,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_BOOL_OR, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, ERRORRECOVERYLEVEL,
			INITIAL_ERRORRECOVERYLEVEL,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_0_TO_2, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, SESSIONTYPE, INITIAL_SESSIONTYPE,
			PHASE_DECLARATIVE, SCOPE_SESSION_WIDE, SENDER_INITIATOR,
			TYPERANGE_SESSIONTYPE, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, IFMARKER, INITIAL_IFMARKER,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_BOOL_AND, USE_INITIAL_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, OFMARKER, INITIAL_OFMARKER,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_BOOL_AND, USE_INITIAL_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, IFMARKINT, INITIAL_IFMARKINT,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_UTF8, USE_INITIAL_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, OFMARKINT, INITIAL_OFMARKINT,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_UTF8, USE_INITIAL_ONLY);
	if (!param)
		goto out;

	/*
	 * Extra parameters for ISER from RFC-5046
	 */
	param = iscsi_set_default_param(pl, RDMAEXTENSIONS, INITIAL_RDMAEXTENSIONS,
			PHASE_OPERATIONAL, SCOPE_SESSION_WIDE, SENDER_BOTH,
			TYPERANGE_BOOL_AND, USE_LEADING_ONLY);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, INITIATORRECVDATASEGMENTLENGTH,
			INITIAL_INITIATORRECVDATASEGMENTLENGTH,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_512_TO_16777215, USE_ALL);
	if (!param)
		goto out;

	param = iscsi_set_default_param(pl, TARGETRECVDATASEGMENTLENGTH,
			INITIAL_TARGETRECVDATASEGMENTLENGTH,
			PHASE_OPERATIONAL, SCOPE_CONNECTION_ONLY, SENDER_BOTH,
			TYPERANGE_512_TO_16777215, USE_ALL);
	if (!param)
		goto out;

	*param_list_ptr = pl;
	return 0;
out:
	iscsi_release_param_list(pl);
	return -1;
}