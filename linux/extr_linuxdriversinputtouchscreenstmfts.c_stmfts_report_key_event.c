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
typedef  int u8 ;
struct stmfts_data {int /*<<< orphan*/  input; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_BACK ; 
 int /*<<< orphan*/  KEY_MENU ; 
#define  STMFTS_MASK_KEY_BACK 129 
#define  STMFTS_MASK_KEY_MENU 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmfts_report_key_event(struct stmfts_data *sdata, const u8 event[])
{
	switch (event[2]) {
	case 0:
		input_report_key(sdata->input, KEY_BACK, 0);
		input_report_key(sdata->input, KEY_MENU, 0);
		break;

	case STMFTS_MASK_KEY_BACK:
		input_report_key(sdata->input, KEY_BACK, 1);
		break;

	case STMFTS_MASK_KEY_MENU:
		input_report_key(sdata->input, KEY_MENU, 1);
		break;

	default:
		dev_warn(&sdata->client->dev,
			 "unknown key event: %#02x\n", event[2]);
		break;
	}

	input_sync(sdata->input);
}