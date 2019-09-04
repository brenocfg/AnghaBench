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
struct p_header95 {int dummy; } ;
struct p_header80 {int dummy; } ;
struct p_header100 {int dummy; } ;
struct drbd_connection {int agreed_pro_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 

unsigned int drbd_header_size(struct drbd_connection *connection)
{
	if (connection->agreed_pro_version >= 100) {
		BUILD_BUG_ON(!IS_ALIGNED(sizeof(struct p_header100), 8));
		return sizeof(struct p_header100);
	} else {
		BUILD_BUG_ON(sizeof(struct p_header80) !=
			     sizeof(struct p_header95));
		BUILD_BUG_ON(!IS_ALIGNED(sizeof(struct p_header80), 8));
		return sizeof(struct p_header80);
	}
}