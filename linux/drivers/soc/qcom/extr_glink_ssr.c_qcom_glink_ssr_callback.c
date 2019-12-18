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
typedef  int /*<<< orphan*/  u32 ;
struct rpmsg_device {int /*<<< orphan*/  dev; } ;
struct glink_ssr {scalar_t__ seq_num; int /*<<< orphan*/  completion; int /*<<< orphan*/  dev; } ;
struct cleanup_done_msg {int /*<<< orphan*/  seq_num; int /*<<< orphan*/  response; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GLINK_SSR_CLEANUP_DONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct glink_ssr* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_glink_ssr_callback(struct rpmsg_device *rpdev,
				   void *data, int len, void *priv, u32 addr)
{
	struct cleanup_done_msg *msg = data;
	struct glink_ssr *ssr = dev_get_drvdata(&rpdev->dev);

	if (len < sizeof(*msg)) {
		dev_err(ssr->dev, "message too short\n");
		return -EINVAL;
	}

	if (le32_to_cpu(msg->version) != 0)
		return -EINVAL;

	if (le32_to_cpu(msg->response) != GLINK_SSR_CLEANUP_DONE)
		return 0;

	if (le32_to_cpu(msg->seq_num) != ssr->seq_num) {
		dev_err(ssr->dev, "invalid sequence number of response\n");
		return -EINVAL;
	}

	complete(&ssr->completion);

	return 0;
}