#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hnae3_handle {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HNS3_DBG_BUF_LEN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  hns3_is_phys_func (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static void hns3_dbg_help(struct hnae3_handle *h)
{
#define HNS3_DBG_BUF_LEN 256

	char printf_buf[HNS3_DBG_BUF_LEN];

	dev_info(&h->pdev->dev, "available commands\n");
	dev_info(&h->pdev->dev, "queue info <number>\n");
	dev_info(&h->pdev->dev, "queue map\n");
	dev_info(&h->pdev->dev, "bd info <q_num> <bd index>\n");

	if (!hns3_is_phys_func(h->pdev))
		return;

	dev_info(&h->pdev->dev, "dump fd tcam\n");
	dev_info(&h->pdev->dev, "dump tc\n");
	dev_info(&h->pdev->dev, "dump tm map <q_num>\n");
	dev_info(&h->pdev->dev, "dump tm\n");
	dev_info(&h->pdev->dev, "dump qos pause cfg\n");
	dev_info(&h->pdev->dev, "dump qos pri map\n");
	dev_info(&h->pdev->dev, "dump qos buf cfg\n");
	dev_info(&h->pdev->dev, "dump mng tbl\n");
	dev_info(&h->pdev->dev, "dump reset info\n");
	dev_info(&h->pdev->dev, "dump m7 info\n");
	dev_info(&h->pdev->dev, "dump ncl_config <offset> <length>(in hex)\n");
	dev_info(&h->pdev->dev, "dump mac tnl status\n");

	memset(printf_buf, 0, HNS3_DBG_BUF_LEN);
	strncat(printf_buf, "dump reg [[bios common] [ssu <port_id>]",
		HNS3_DBG_BUF_LEN - 1);
	strncat(printf_buf + strlen(printf_buf),
		" [igu egu <port_id>] [rpu <tc_queue_num>]",
		HNS3_DBG_BUF_LEN - strlen(printf_buf) - 1);
	strncat(printf_buf + strlen(printf_buf),
		" [rtc] [ppp] [rcb] [tqp <queue_num>]]\n",
		HNS3_DBG_BUF_LEN - strlen(printf_buf) - 1);
	dev_info(&h->pdev->dev, "%s", printf_buf);

	memset(printf_buf, 0, HNS3_DBG_BUF_LEN);
	strncat(printf_buf, "dump reg dcb <port_id> <pri_id> <pg_id>",
		HNS3_DBG_BUF_LEN - 1);
	strncat(printf_buf + strlen(printf_buf), " <rq_id> <nq_id> <qset_id>\n",
		HNS3_DBG_BUF_LEN - strlen(printf_buf) - 1);
	dev_info(&h->pdev->dev, "%s", printf_buf);
}