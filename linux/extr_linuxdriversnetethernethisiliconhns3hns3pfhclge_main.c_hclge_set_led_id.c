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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int dummy; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_ID_ACTIVE 129 
#define  ETHTOOL_ID_INACTIVE 128 
 int /*<<< orphan*/  HCLGE_LED_OFF ; 
 int /*<<< orphan*/  HCLGE_LED_ON ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int hclge_set_led_status (struct hclge_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_set_led_id(struct hnae3_handle *handle,
			    enum ethtool_phys_id_state status)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	switch (status) {
	case ETHTOOL_ID_ACTIVE:
		return hclge_set_led_status(hdev, HCLGE_LED_ON);
	case ETHTOOL_ID_INACTIVE:
		return hclge_set_led_status(hdev, HCLGE_LED_OFF);
	default:
		return -EINVAL;
	}
}