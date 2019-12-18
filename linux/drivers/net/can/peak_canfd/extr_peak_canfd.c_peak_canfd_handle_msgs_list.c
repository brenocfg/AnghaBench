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
struct pucan_rx_msg {int dummy; } ;
struct peak_canfd_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int peak_canfd_handle_msg (struct peak_canfd_priv*,void*) ; 

int peak_canfd_handle_msgs_list(struct peak_canfd_priv *priv,
				struct pucan_rx_msg *msg_list, int msg_count)
{
	void *msg_ptr = msg_list;
	int i, msg_size = 0;

	for (i = 0; i < msg_count; i++) {
		msg_size = peak_canfd_handle_msg(priv, msg_ptr);

		/* a null packet can be found at the end of a list */
		if (msg_size <= 0)
			break;

		msg_ptr += ALIGN(msg_size, 4);
	}

	if (msg_size < 0)
		return msg_size;

	return i;
}