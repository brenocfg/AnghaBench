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
typedef  int /*<<< orphan*/  u8 ;
struct st95hf_context {int dummy; } ;
struct nfc_digital_dev {int /*<<< orphan*/  curr_rf_tech; } ;

/* Variables and functions */
 struct st95hf_context* nfc_digital_get_drvdata (struct nfc_digital_dev*) ; 
 int rf_off (struct st95hf_context*) ; 
 int st95hf_select_protocol (struct st95hf_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st95hf_switch_rf(struct nfc_digital_dev *ddev, bool on)
{
	u8 rf_tech;
	struct st95hf_context *stcontext = nfc_digital_get_drvdata(ddev);

	rf_tech = ddev->curr_rf_tech;

	if (on)
		/* switch on RF field */
		return st95hf_select_protocol(stcontext, rf_tech);

	/* switch OFF RF field */
	return rf_off(stcontext);
}