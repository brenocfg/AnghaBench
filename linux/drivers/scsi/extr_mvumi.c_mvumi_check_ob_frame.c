#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mvumi_rsp_frame {unsigned short request_id; unsigned short tag; } ;
struct TYPE_4__ {unsigned short size; } ;
struct mvumi_hba {unsigned int ob_max_size; TYPE_3__** tag_cmd; TYPE_2__* pdev; scalar_t__ request_id_enabled; TYPE_1__ tag_pool; struct mvumi_rsp_frame* ob_list; } ;
struct TYPE_6__ {unsigned short request_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static char mvumi_check_ob_frame(struct mvumi_hba *mhba,
		unsigned int cur_obf, struct mvumi_rsp_frame *p_outb_frame)
{
	unsigned short tag, request_id;

	udelay(1);
	p_outb_frame = mhba->ob_list + cur_obf * mhba->ob_max_size;
	request_id = p_outb_frame->request_id;
	tag = p_outb_frame->tag;
	if (tag > mhba->tag_pool.size) {
		dev_err(&mhba->pdev->dev, "ob frame data error\n");
		return -1;
	}
	if (mhba->tag_cmd[tag] == NULL) {
		dev_err(&mhba->pdev->dev, "tag[0x%x] with NO command\n", tag);
		return -1;
	} else if (mhba->tag_cmd[tag]->request_id != request_id &&
						mhba->request_id_enabled) {
			dev_err(&mhba->pdev->dev, "request ID from FW:0x%x,"
					"cmd request ID:0x%x\n", request_id,
					mhba->tag_cmd[tag]->request_id);
			return -1;
	}

	return 0;
}