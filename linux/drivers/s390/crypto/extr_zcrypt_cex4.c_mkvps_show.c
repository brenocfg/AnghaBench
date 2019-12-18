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
struct zcrypt_queue {int /*<<< orphan*/  online; TYPE_1__* queue; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cca_info {char new_mk_state; char cur_mk_state; char old_mk_state; int /*<<< orphan*/  old_mkvp; int /*<<< orphan*/  cur_mkvp; int /*<<< orphan*/  new_mkvp; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  ci ;
struct TYPE_4__ {struct zcrypt_queue* private; } ;
struct TYPE_3__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_QID_CARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_QUEUE (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  cca_get_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cca_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cca_info*,int /*<<< orphan*/ ,int) ; 
 int snprintf (char*,scalar_t__,char*,...) ; 
 TYPE_2__* to_ap_queue (struct device*) ; 

__attribute__((used)) static ssize_t mkvps_show(struct device *dev,
			  struct device_attribute *attr,
			  char *buf)
{
	int n = 0;
	struct cca_info ci;
	struct zcrypt_queue *zq = to_ap_queue(dev)->private;
	static const char * const cao_state[] = { "invalid", "valid" };
	static const char * const new_state[] = { "empty", "partial", "full" };

	memset(&ci, 0, sizeof(ci));

	cca_get_info(AP_QID_CARD(zq->queue->qid),
		     AP_QID_QUEUE(zq->queue->qid),
		     &ci, zq->online);

	if (ci.new_mk_state >= '1' && ci.new_mk_state <= '3')
		n = snprintf(buf, PAGE_SIZE, "AES NEW: %s 0x%016llx\n",
			     new_state[ci.new_mk_state - '1'], ci.new_mkvp);
	else
		n = snprintf(buf, PAGE_SIZE, "AES NEW: - -\n");

	if (ci.cur_mk_state >= '1' && ci.cur_mk_state <= '2')
		n += snprintf(buf + n, PAGE_SIZE - n, "AES CUR: %s 0x%016llx\n",
			      cao_state[ci.cur_mk_state - '1'], ci.cur_mkvp);
	else
		n += snprintf(buf + n, PAGE_SIZE - n, "AES CUR: - -\n");

	if (ci.old_mk_state >= '1' && ci.old_mk_state <= '2')
		n += snprintf(buf + n, PAGE_SIZE - n, "AES OLD: %s 0x%016llx\n",
			      cao_state[ci.old_mk_state - '1'], ci.old_mkvp);
	else
		n += snprintf(buf + n, PAGE_SIZE - n, "AES OLD: - -\n");

	return n;
}