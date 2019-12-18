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
struct netvsc_device_info {int /*<<< orphan*/  recv_section_size; int /*<<< orphan*/  recv_sections; int /*<<< orphan*/  send_section_size; int /*<<< orphan*/  send_sections; int /*<<< orphan*/  num_chn; int /*<<< orphan*/  rss_key; } ;
struct netvsc_device {TYPE_1__* extension; int /*<<< orphan*/  recv_section_size; int /*<<< orphan*/  recv_section_cnt; int /*<<< orphan*/  send_section_size; int /*<<< orphan*/  send_section_cnt; int /*<<< orphan*/  num_chn; } ;
struct TYPE_2__ {int /*<<< orphan*/  rss_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETVSC_DEFAULT_RX ; 
 int /*<<< orphan*/  NETVSC_DEFAULT_TX ; 
 int /*<<< orphan*/  NETVSC_HASH_KEYLEN ; 
 int /*<<< orphan*/  NETVSC_RECV_SECTION_SIZE ; 
 int /*<<< orphan*/  NETVSC_SEND_SECTION_SIZE ; 
 int /*<<< orphan*/  VRSS_CHANNEL_DEFAULT ; 
 struct netvsc_device_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct netvsc_device_info *netvsc_devinfo_get
			(struct netvsc_device *nvdev)
{
	struct netvsc_device_info *dev_info;

	dev_info = kzalloc(sizeof(*dev_info), GFP_ATOMIC);

	if (!dev_info)
		return NULL;

	if (nvdev) {
		dev_info->num_chn = nvdev->num_chn;
		dev_info->send_sections = nvdev->send_section_cnt;
		dev_info->send_section_size = nvdev->send_section_size;
		dev_info->recv_sections = nvdev->recv_section_cnt;
		dev_info->recv_section_size = nvdev->recv_section_size;

		memcpy(dev_info->rss_key, nvdev->extension->rss_key,
		       NETVSC_HASH_KEYLEN);
	} else {
		dev_info->num_chn = VRSS_CHANNEL_DEFAULT;
		dev_info->send_sections = NETVSC_DEFAULT_TX;
		dev_info->send_section_size = NETVSC_SEND_SECTION_SIZE;
		dev_info->recv_sections = NETVSC_DEFAULT_RX;
		dev_info->recv_section_size = NETVSC_RECV_SECTION_SIZE;
	}

	return dev_info;
}