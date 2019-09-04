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
struct pluto {TYPE_1__* pdev; } ;
struct firmware {int dummy; } ;
struct dvb_frontend {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct pluto* frontend_to_pluto (struct dvb_frontend*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pluto2_request_firmware(struct dvb_frontend *fe,
				   const struct firmware **fw, char *name)
{
	struct pluto *pluto = frontend_to_pluto(fe);

	return request_firmware(fw, name, &pluto->pdev->dev);
}