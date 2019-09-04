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
struct omap_des_dev {int /*<<< orphan*/  engine; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 int crypto_transfer_ablkcipher_request_to_engine (int /*<<< orphan*/ ,struct ablkcipher_request*) ; 

__attribute__((used)) static int omap_des_handle_queue(struct omap_des_dev *dd,
				 struct ablkcipher_request *req)
{
	if (req)
		return crypto_transfer_ablkcipher_request_to_engine(dd->engine, req);

	return 0;
}