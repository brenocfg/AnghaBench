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
struct qed_ooo_buffer {int /*<<< orphan*/  rx_buffer_phys_addr; } ;
struct qed_ll2_info {int /*<<< orphan*/  my_id; } ;
struct qed_hwfn {int /*<<< orphan*/  p_ooo_info; } ;

/* Variables and functions */
 int qed_ll2_post_rx_buffer (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_ooo_buffer*,int) ; 
 struct qed_ooo_buffer* qed_ooo_get_free_buffer (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_ooo_put_free_buffer (struct qed_hwfn*,int /*<<< orphan*/ ,struct qed_ooo_buffer*) ; 

__attribute__((used)) static void
qed_ooo_submit_rx_buffers(struct qed_hwfn *p_hwfn,
			  struct qed_ll2_info *p_ll2_conn)
{
	struct qed_ooo_buffer *p_buffer;
	int rc;

	while ((p_buffer = qed_ooo_get_free_buffer(p_hwfn,
						   p_hwfn->p_ooo_info))) {
		rc = qed_ll2_post_rx_buffer(p_hwfn,
					    p_ll2_conn->my_id,
					    p_buffer->rx_buffer_phys_addr,
					    0, p_buffer, true);
		if (rc) {
			qed_ooo_put_free_buffer(p_hwfn,
						p_hwfn->p_ooo_info, p_buffer);
			break;
		}
	}
}