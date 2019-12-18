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
struct vmlogrdr_priv_t {char* recording_name; } ;
typedef  int /*<<< orphan*/  cp_response ;
typedef  int /*<<< orphan*/  cp_command ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  cpcmd (char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int recording_class_AB ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int vmlogrdr_recording(struct vmlogrdr_priv_t * logptr,
			      int action, int purge)
{

	char cp_command[80];
	char cp_response[160];
	char *onoff, *qid_string;
	int rc;

	onoff = ((action == 1) ? "ON" : "OFF");
	qid_string = ((recording_class_AB == 1) ? " QID * " : "");

	/*
	 * The recording commands needs to be called with option QID
	 * for guests that have previlege classes A or B.
	 * Purging has to be done as separate step, because recording
	 * can't be switched on as long as records are on the queue.
	 * Doing both at the same time doesn't work.
	 */
	if (purge && (action == 1)) {
		memset(cp_command, 0x00, sizeof(cp_command));
		memset(cp_response, 0x00, sizeof(cp_response));
		snprintf(cp_command, sizeof(cp_command),
			 "RECORDING %s PURGE %s",
			 logptr->recording_name,
			 qid_string);
		cpcmd(cp_command, cp_response, sizeof(cp_response), NULL);
	}

	memset(cp_command, 0x00, sizeof(cp_command));
	memset(cp_response, 0x00, sizeof(cp_response));
	snprintf(cp_command, sizeof(cp_command), "RECORDING %s %s %s",
		logptr->recording_name,
		onoff,
		qid_string);
	cpcmd(cp_command, cp_response, sizeof(cp_response), NULL);
	/* The recording command will usually answer with 'Command complete'
	 * on success, but when the specific service was never connected
	 * before then there might be an additional informational message
	 * 'HCPCRC8072I Recording entry not found' before the
	 * 'Command complete'. So I use strstr rather then the strncmp.
	 */
	if (strstr(cp_response,"Command complete"))
		rc = 0;
	else
		rc = -EIO;
	/*
	 * If we turn recording off, we have to purge any remaining records
	 * afterwards, as a large number of queued records may impact z/VM
	 * performance.
	 */
	if (purge && (action == 0)) {
		memset(cp_command, 0x00, sizeof(cp_command));
		memset(cp_response, 0x00, sizeof(cp_response));
		snprintf(cp_command, sizeof(cp_command),
			 "RECORDING %s PURGE %s",
			 logptr->recording_name,
			 qid_string);
		cpcmd(cp_command, cp_response, sizeof(cp_response), NULL);
	}

	return rc;
}