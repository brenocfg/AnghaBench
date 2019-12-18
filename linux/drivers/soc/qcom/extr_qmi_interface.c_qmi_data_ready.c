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
struct sock {struct qmi_handle* sk_user_data; } ;
struct qmi_handle {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qmi_data_ready(struct sock *sk)
{
	struct qmi_handle *qmi = sk->sk_user_data;

	/*
	 * This will be NULL if we receive data while being in
	 * qmi_handle_release()
	 */
	if (!qmi)
		return;

	queue_work(qmi->wq, &qmi->work);
}