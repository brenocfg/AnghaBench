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
struct hsi_msg {int /*<<< orphan*/  cl; } ;
struct hsc_client_data {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSC_RXBREAK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hsc_client_data* hsi_client_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsi_free_msg (struct hsi_msg*) ; 

__attribute__((used)) static void hsc_break_req_destructor(struct hsi_msg *msg)
{
	struct hsc_client_data *cl_data = hsi_client_drvdata(msg->cl);

	hsi_free_msg(msg);
	clear_bit(HSC_RXBREAK, &cl_data->flags);
}