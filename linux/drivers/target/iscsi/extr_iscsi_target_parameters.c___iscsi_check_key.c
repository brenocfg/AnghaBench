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
struct iscsi_param_list {int dummy; } ;
struct iscsi_param {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SENDER_INITIATOR (struct iscsi_param*) ; 
 int /*<<< orphan*/  IS_SENDER_TARGET (struct iscsi_param*) ; 
 scalar_t__ KEY_MAXLEN ; 
 int SENDER_INITIATOR ; 
 int SENDER_RECEIVER ; 
 int SENDER_TARGET ; 
 struct iscsi_param* iscsi_find_param_from_key (char*,struct iscsi_param_list*) ; 
 int /*<<< orphan*/  pr_err (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static struct iscsi_param *__iscsi_check_key(
	char *key,
	int sender,
	struct iscsi_param_list *param_list)
{
	struct iscsi_param *param;

	if (strlen(key) > KEY_MAXLEN) {
		pr_err("Length of key name \"%s\" exceeds %d.\n",
			key, KEY_MAXLEN);
		return NULL;
	}

	param = iscsi_find_param_from_key(key, param_list);
	if (!param)
		return NULL;

	if ((sender & SENDER_INITIATOR) && !IS_SENDER_INITIATOR(param)) {
		pr_err("Key \"%s\" may not be sent to %s,"
			" protocol error.\n", param->name,
			(sender & SENDER_RECEIVER) ? "target" : "initiator");
		return NULL;
	}

	if ((sender & SENDER_TARGET) && !IS_SENDER_TARGET(param)) {
		pr_err("Key \"%s\" may not be sent to %s,"
			" protocol error.\n", param->name,
			(sender & SENDER_RECEIVER) ? "initiator" : "target");
		return NULL;
	}

	return param;
}