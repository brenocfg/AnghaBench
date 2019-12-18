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
struct sk_buff {int dummy; } ;
struct rtw_coex {int /*<<< orphan*/  mutex; int /*<<< orphan*/  queue; int /*<<< orphan*/  wait; } ;
struct rtw_dev {struct rtw_coex coex; } ;
struct rtw_coex_info_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEX_REQUEST_TIMEOUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_fw_query_bt_mp_info (struct rtw_dev*,struct rtw_coex_info_req*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *rtw_coex_info_request(struct rtw_dev *rtwdev,
					     struct rtw_coex_info_req *req)
{
	struct rtw_coex *coex = &rtwdev->coex;
	struct sk_buff *skb_resp = NULL;

	mutex_lock(&coex->mutex);

	rtw_fw_query_bt_mp_info(rtwdev, req);

	if (!wait_event_timeout(coex->wait, !skb_queue_empty(&coex->queue),
				COEX_REQUEST_TIMEOUT)) {
		rtw_err(rtwdev, "coex request time out\n");
		goto out;
	}

	skb_resp = skb_dequeue(&coex->queue);
	if (!skb_resp) {
		rtw_err(rtwdev, "failed to get coex info response\n");
		goto out;
	}

out:
	mutex_unlock(&coex->mutex);
	return skb_resp;
}