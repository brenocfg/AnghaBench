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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  TPS658621A 133 
#define  TPS658621CD 132 
#define  TPS658623 131 
#define  TPS658640 130 
#define  TPS658640v2 129 
#define  TPS658643 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,int) ; 

__attribute__((used)) static void tps6586x_print_version(struct i2c_client *client, int version)
{
	const char *name;

	switch (version) {
	case TPS658621A:
		name = "TPS658621A";
		break;
	case TPS658621CD:
		name = "TPS658621C/D";
		break;
	case TPS658623:
		name = "TPS658623";
		break;
	case TPS658640:
	case TPS658640v2:
		name = "TPS658640";
		break;
	case TPS658643:
		name = "TPS658643";
		break;
	default:
		name = "TPS6586X";
		break;
	}

	dev_info(&client->dev, "Found %s, VERSIONCRC is %02x\n", name, version);
}