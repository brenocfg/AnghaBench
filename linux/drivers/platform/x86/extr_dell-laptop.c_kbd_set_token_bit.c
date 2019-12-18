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
typedef  size_t u8 ;
struct calling_interface_token {int /*<<< orphan*/  value; int /*<<< orphan*/  location; } ;
struct calling_interface_buffer {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLASS_TOKEN_WRITE ; 
 int EINVAL ; 
 int /*<<< orphan*/  SELECT_TOKEN_STD ; 
 int /*<<< orphan*/  dell_fill_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dell_send_request (struct calling_interface_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct calling_interface_token* dell_smbios_find_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kbd_tokens ; 

__attribute__((used)) static int kbd_set_token_bit(u8 bit)
{
	struct calling_interface_buffer buffer;
	struct calling_interface_token *token;
	int ret;

	if (bit >= ARRAY_SIZE(kbd_tokens))
		return -EINVAL;

	token = dell_smbios_find_token(kbd_tokens[bit]);
	if (!token)
		return -EINVAL;

	dell_fill_request(&buffer, token->location, token->value, 0, 0);
	ret = dell_send_request(&buffer, CLASS_TOKEN_WRITE, SELECT_TOKEN_STD);

	return ret;
}