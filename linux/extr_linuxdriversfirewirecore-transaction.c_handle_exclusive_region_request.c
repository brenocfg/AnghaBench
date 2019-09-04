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
struct fw_request {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct fw_packet {int /*<<< orphan*/  generation; int /*<<< orphan*/ * header; } ;
struct fw_card {int dummy; } ;
struct fw_address_handler {int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* address_callback ) (struct fw_card*,struct fw_request*,int,int,int,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int HEADER_GET_DESTINATION (int /*<<< orphan*/ ) ; 
 int HEADER_GET_EXTENDED_TCODE (int /*<<< orphan*/ ) ; 
 int HEADER_GET_SOURCE (int /*<<< orphan*/ ) ; 
 int HEADER_GET_TCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCODE_ADDRESS_ERROR ; 
 int TCODE_LOCK_REQUEST ; 
 int /*<<< orphan*/  address_handler_list ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int /*<<< orphan*/ ) ; 
 struct fw_address_handler* lookup_enclosing_address_handler (int /*<<< orphan*/ *,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct fw_card*,struct fw_request*,int,int,int,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_exclusive_region_request(struct fw_card *card,
					    struct fw_packet *p,
					    struct fw_request *request,
					    unsigned long long offset)
{
	struct fw_address_handler *handler;
	int tcode, destination, source;

	destination = HEADER_GET_DESTINATION(p->header[0]);
	source      = HEADER_GET_SOURCE(p->header[1]);
	tcode       = HEADER_GET_TCODE(p->header[0]);
	if (tcode == TCODE_LOCK_REQUEST)
		tcode = 0x10 + HEADER_GET_EXTENDED_TCODE(p->header[3]);

	rcu_read_lock();
	handler = lookup_enclosing_address_handler(&address_handler_list,
						   offset, request->length);
	if (handler)
		handler->address_callback(card, request,
					  tcode, destination, source,
					  p->generation, offset,
					  request->data, request->length,
					  handler->callback_data);
	rcu_read_unlock();

	if (!handler)
		fw_send_response(card, request, RCODE_ADDRESS_ERROR);
}