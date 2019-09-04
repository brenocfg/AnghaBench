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
struct scatterlist {int dummy; } ;
struct port {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPIPE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int __send_to_port (struct port*,struct scatterlist*,int,int,void*,int) ; 
 int early_put_chars (int /*<<< orphan*/ ,char const*,int) ; 
 struct port* find_port_by_vtermno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,void*,int) ; 
 scalar_t__ unlikely (int (*) (int /*<<< orphan*/ ,char const*,int)) ; 

__attribute__((used)) static int put_chars(u32 vtermno, const char *buf, int count)
{
	struct port *port;
	struct scatterlist sg[1];
	void *data;
	int ret;

	if (unlikely(early_put_chars))
		return early_put_chars(vtermno, buf, count);

	port = find_port_by_vtermno(vtermno);
	if (!port)
		return -EPIPE;

	data = kmemdup(buf, count, GFP_ATOMIC);
	if (!data)
		return -ENOMEM;

	sg_init_one(sg, data, count);
	ret = __send_to_port(port, sg, 1, count, data, false);
	kfree(data);
	return ret;
}